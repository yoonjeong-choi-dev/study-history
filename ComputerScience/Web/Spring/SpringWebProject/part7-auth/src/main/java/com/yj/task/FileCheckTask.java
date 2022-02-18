package com.yj.task;

import com.yj.controller.UploadController;
import com.yj.domain.BoardAttachFileVO;
import com.yj.mapper.BoardAttachFileMapper;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Component;

import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

@Log4j
@Component
public class FileCheckTask {

    @Setter(onMethod_ = @Autowired)
    private BoardAttachFileMapper boardAttachFileMapper;

    //@Scheduled(cron = "0 * * * * *")    // 테스트용
    @Scheduled(cron = "0 0 2 * * *")    //매일 새벽 2시
    public void checkFiles() throws Exception {
        log.warn("File Check Task is running ===================> : " + getFolderYesterday());
        log.warn(new Date());

        String basePath = UploadController.getUploadPath();

        // 데이터베이스의 파일 목록
        List<BoardAttachFileVO> fileList = boardAttachFileMapper.getOldFiles();
        List<Path> filePaths = fileList.stream().map(file ->
                        Paths.get(basePath, file.getUploadPath(), file.getUuid() + "_" + file.getFileName()))
                .collect(Collectors.toList());
        fileList.stream().filter(file -> file.getIsImage() == 1)
                .map(file ->
                        Paths.get(basePath, file.getUploadPath(), "s_" + file.getUuid() + "_" + file.getFileName()))
                .forEach(path -> filePaths.add(path));

        log.warn("============================================================");
        filePaths.forEach(path -> log.warn(path));
        log.warn("============================================================");

        // 스토리지 체크
        File targetDir = Paths.get(basePath, getFolderYesterday()).toFile();
        File[] toRemove = targetDir.listFiles(file -> !filePaths.contains(file.toPath()));

        // 삭제
        for (File file : toRemove) {
            log.warn("Removed : " + file.getAbsolutePath());
            file.delete();
        }
    }

    private String getFolderYesterday() {
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, -1);

        String ret = sdf.format(cal.getTime());
        return ret.replace("-", File.separator);
    }
}
