const fetchUser = async () => {
    try {
        const res = await axios.get('/users');
        const users = res.data;

        // 유저 정보를 출력
        const userTableBody = document.querySelector('#user-list tbody');
        userTableBody.innerHTML = '';
        users.map((user) => {
            // 클릭 시, 댓글 출력
            const row = document.createElement('tr');
            row.addEventListener('click', () => {
                fetchComment(user._id);
            });

            // 유저의 각 필드 정보 출력
            let td = document.createElement('td');
            td.textContent = user._id;
            row.appendChild(td);

            td = document.createElement('td');
            td.textContent = user.name;
            row.appendChild(td);

            td = document.createElement('td');
            td.textContent = user.age;
            row.appendChild(td);

            td = document.createElement('td');
            td.textContent = user.married ? '기혼' : '미혼';
            row.appendChild(td);

            // 소개가 있는 경우만 출력
            if (user.comment) {
                td = document.createElement('td');
                td.textContent = user.comment;
                row.appendChild(td);
            }

            userTableBody.appendChild(row);
        });

    } catch (err) {
        console.error(err);
    }
};

const fetchComment = async (userId) => {
    try {
        const res = await axios.get(`/users/${userId}/comments`);
        const comments = res.data;

        // 댓글 정보 출력
        const commentTableBody = document.querySelector('#comment-list tbody');
        commentTableBody.innerHTML = '';
        comments.map(function (comment) {
            // 댓글의 각 필드 정보 출력
            const row = document.createElement('tr');
            let td = document.createElement('td');
            td.textContent = comment._id;
            row.appendChild(td);
            td = document.createElement('td');
            td.textContent = comment.commenter.name;
            row.appendChild(td);
            td = document.createElement('td');
            td.textContent = comment.comment;
            row.appendChild(td);

            // 댓글 수정 버튼
            const edit = document.createElement('button');
            edit.textContent = '수정';
            edit.addEventListener('click', async () => {
                const newComment = prompt('바꿀 내용을 입력하세요');
                if (!newComment) {
                    return alert('내용을 반드시 입력하셔야 합니다');
                }
                try {
                    // PUT 메서드 호출
                    await axios.patch(`/comments/${comment._id}`, { comment: newComment });
                    fetchComment(userId);
                } catch (err) {
                    console.error(err);
                }
            });

            // 댓글 삭제 버튼
            const remove = document.createElement('button');
            remove.textContent = '삭제';
            remove.addEventListener('click', async () => {
                try {
                    // DELETE 호출
                    await axios.delete(`/comments/${comment._id}`);
                    fetchComment(userId);
                } catch (err) {
                    console.error(err);
                }
            });

            // 수정,삭제 버튼 추가
            td = document.createElement('td');
            td.appendChild(edit);
            row.appendChild(td);
            td = document.createElement('td');
            td.appendChild(remove);
            row.appendChild(td);
            commentTableBody.appendChild(row);
        });
    } catch (err) {
        console.error(err);
    }
};

// 사용자 이름 눌렀을 때 댓글 로딩
document.querySelectorAll('#user-list tr').forEach((elem) => {
    elem.addEventListener('click', function () {
        const id = elem.querySelector('td').textContent;
        fetchComment(id);
    });
});

// 사용자 등록 이벤트
const user_form = document.getElementById('user-form');
user_form.addEventListener('submit', async (e) => {
    e.preventDefault();

    const name = e.target.username.value;
    const age = e.target.age.value;
    const married = e.target.married.checked;
    const comment = e.target.comment.value;

    if (!name) {
        return alert('이름을 입력하세요');
    }
    if (!age) {
        return alert('나이를 입력하세요');
    }
    try {
        if (!comment) await axios.post('/users', { name, age, married });
        else await axios.post('/users', { name, age, married, comment });

        fetchUser();
    } catch (err) {
        console.error(err);
    }
    e.target.username.value = '';
    e.target.age.value = '';
    e.target.married.checked = false;
    e.target.comment.value = '';
});

// 댓글 등록 
const comment_form = document.getElementById('comment-form');
comment_form.addEventListener('submit', async (e) => {
    e.preventDefault();
    const id = e.target.userid.value;
    const comment = e.target.comment.value;
    if (!id) {
        return alert('아이디를 입력하세요');
    }
    if (!comment) {
        return alert('댓글을 입력하세요');
    }
    try {
        await axios.post('/comments', { id, comment });
        fetchComment(id);
    } catch (err) {
        console.error(err);
    }
    e.target.userid.value = '';
    e.target.comment.value = '';
});