// 로드시 사용자 정보 fetch 함수
const fetchUser = async () => {
    try {
        // 유저 정보 GET
        const res = await axios.get("/users");
        const users = res.data;
        
        // rendering
        const list = document.getElementById('list');
        list.innerHTML = '';
        Object.keys(users).map((key) => {
            const userDiv = document.createElement('div');
            const span = document.createElement('span');
            span.textContent = users[key];

            const editButton = document.createElement('button');
            editButton.textContent = 'Edit';
            editButton.addEventListener('click', async () => {
                const name = prompt("Enter name :");
                if (!name) {
                    return alert("Please enter name");
                }

                // PUT call
                try {
                    await axios.put('/user/' + key, { name });
                    fetchUser();
                } catch (err) {
                    console.error(err);
                }
            });

            const removeButton = document.createElement('button');
            removeButton.textContent = 'Delete';
            removeButton.addEventListener('click', async () => {
                // DELETE call
                try {
                    await axios.delete('/user/' + key);
                    fetchUser();
                } catch (err) {
                    console.error(err);
                }
            });

            userDiv.appendChild(span);
            userDiv.appendChild(editButton);
            userDiv.appendChild(removeButton);
            list.appendChild(userDiv);
        });
    } catch (err) {
        console.error(err);
    }
}

window.onload = fetchUser;

// 폼 제출 함수
document.getElementById('form').addEventListener('submit', async (e) => {
    e.preventDefault();

    const name = e.target.username.value;
    if (!name) {
        return alert("Please enter name");
    }

    // POST call
    try {
        await axios.post('/user', { name });
        fetchUser();
    } catch (err) {
        console.error(err);
    }

    // Initialize input
    e.target.username.value = '';
})