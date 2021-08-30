#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#define NLOOP_FOR_ESTIMATION 1000000000UL
#define NSECS_PER_MSEC 1000000UL
#define NSECS_PER_SEC 1000000000UL

static unsigned long nloop_per_resol;   // 루프 실행 테스트의 루프 횟수
static struct timespec start;

/**
 * @brief 
 * - 나노초 단위로 after - before 시간 측정
 * - timespec
 *  - 나노초까지 측정 가능
 *  - tv_sec : 초 단위
 *  - tv_nsec : 나도초 단위
 * 
 * @param before 시작 시간
 * @param after 종료 시간
 * 
 * @return after-before 나노초
 */
static inline long diff_nsec(struct timespec before, struct timespec after)
{

    return (
        (after.tv_sec * NSECS_PER_SEC + after.tv_nsec) -
        (before.tv_sec * NSECS_PER_SEC + before.tv_nsec));
}

/**
 * @brief 
 * CPU 시간을 1밀리초 단위로 사용처리에 필요한 계산량을 추정
 * 1밀리초에 도는 루프 횟수 측정
 * 
 * @return 1밀리초에 도는 루프 횟수
 */
static unsigned long long estimate_loops_per_msec()
{
    // 시작 시간 측정
    struct timespec before;
    clock_gettime(CLOCK_MONOTONIC, &before);

    // NLOOP_FOR_ESTIMATION 만큼 루프 실행
    unsigned long i;
    for (i = 0; i < NLOOP_FOR_ESTIMATION; i++)
        ;

    // 종료 시간 측정
    struct timespec after;
    clock_gettime(CLOCK_MONOTONIC, &after);

    // 1밀리초에 도는 루프 횟수 측정
    int ret = NLOOP_FOR_ESTIMATION * NSECS_PER_MSEC / diff_nsec(before, after);
    return ret;
}
/**
 * @brief nloop만큼 루프를 도는 함수
 * 
 * @param nloop 실행시킬 루프 횟수
 */

static inline void load(unsigned long nloop)
{
    unsigned long i;
    for (i = 0; i < nloop; i++)
        ;
}

/**
 * @brief 
 * 각 프로세스를 동작시켜 CPU 실행 시간을 측정하는 함수
 *  - 자식 프로세스 생성이 성공하면 호출되는 함수
 *  - 이 함수를 호출한 프로세스에 대해서 루프 테스트 실행
 * 
 * @param id 자식 프로세스 id
 * @param buf 실행 시간 결과를 저장하는 버퍼
 * @param nrecord 루프 실행 테스트 실행 횟수
 * @param start 시작 시간
 */
static void child_fn(int id, struct timespec *buf, int nrecord, struct timespec start)
{
    int i;

    // nloop_per_resol만큼의 루프를 실행시킬 때 걸리는 시간 기록
    // 프로세스 스케쥴러에 의해 한번에 실행되지 않는다
    for (i = 0; i < nrecord; i++)
    {
        struct timespec ts;

        load(nloop_per_resol);
        clock_gettime(CLOCK_MONOTONIC, &ts);
        buf[i] = ts;
    }

    // 결과 출력
    printf("%8s\t%8s\t%8s\n", "pid", "duration", "progress");
    for (i = 0; i < nrecord; i++)
    {
        printf("%8d\t%8ld\t%8d\n",
               id, diff_nsec(start, buf[i]) / NSECS_PER_MSEC, (i + 1) * 100 / nrecord);
    }

    // 프로세스 종료
    exit(EXIT_SUCCESS);
}



static pid_t *pids;

int main(int argc, char *argv[])
{
    int ret = EXIT_FAILURE;

    if (argc < 3)
    {
        fprintf(stderr, "usage : %s <total[ms]> <resolution[ms]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nproc = 10; // 동시 동작하는 프로세스 개수
    int total = atoi(argv[1]); // 프로그램이 동작하는 총 시간
    int resol = atoi(argv[2]); // 데이터 수집 간격

    if (total < 1)
    {
        fprintf(stderr, "<total>(%d) should be >= 1\n", total);
        exit(EXIT_FAILURE);
    }

    if (resol < 1)
    {
        fprintf(stderr, "<resol>(%d) should be >= 1\n", resol);
        exit(EXIT_FAILURE);
    }

    if (total % resol)
    {
        fprintf(stderr, "<total>(%d) should be multiple of <resolution>(%d)\n",
                total, resol);
        exit(EXIT_FAILURE);
    }

    int nrecord = total / resol;

    // 각 프로세스의 수집 데이터를 저장하는 버퍼
    struct timespec *logbuf = malloc(nrecord * sizeof(struct timespec));
    if (logbuf == NULL)
        err(EXIT_FAILURE, "malloc(logbuf) failed");


    // 데이터 수집 간격동안 실행시켜야 하는 루프 횟수 계산
    puts("estimating workload which takes just one millisecond");
    nloop_per_resol = estimate_loops_per_msec() * resol;
    puts("end estimate");
    fflush(stdout);

    // 자식 프로세스 생성 결과를 저장할 배열 생성
    pids = malloc(nproc * sizeof(pid_t));
    if (pids == NULL)
        err(EXIT_FAILURE, "failed to allocate pid table");
    

    // 시작 시간 측정
    clock_gettime(CLOCK_MONOTONIC, &start);

    ret = EXIT_SUCCESS;
    

    // 자식 프로세스 생성
    int i, ncreated;
    for (i = 0, ncreated = 0; i < nproc; i++, ncreated++)
    {
        pids[i] = fork();
        if(pids[i] < 0){
            // 프로세스 생성 실패시, 지금까지 생성했던 프로세스 종료 후 테스트 탈출
            int j;
            for(j=0;j<ncreated;j++)
                kill(pids[j], SIGKILL);
            ret = EXIT_FAILURE;
            break;
        }
        else if(pids[i] == 0){
            // 자식 프로세스 생성 성공 시 : 각 프로세스 실행
            // 5번째 프로세스의 경우 우선순위를 낮춘다
            if(i==5)
                nice(5);
            child_fn(i, logbuf, nrecord, start);

            // 도달할 수 없는 부분
            abort();
        }
    }

    
    // 부모 프로세스
    // 모든 자식 프로세스가 종료할 때까지 대기한다
    for (i = 0; i < ncreated; i++)
        if (wait(NULL) < 0)
            warn("wait() failed.");

    
    exit(ret);
}