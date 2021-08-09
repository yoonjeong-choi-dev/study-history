import React, { useState, useEffect, memo } from "react";import { saveJSONToStorage, loadJSONFromStorage } from "./localStrorageController";

const getUserDataFromStorage = (id) => loadJSONFromStorage(`userid:${id}`);

const saveUserDataToStorage = (userData) => {
    if (!userData) return;

    const {id, first_name, second_name, avatar, email } = userData;
    saveJSONToStorage(`userid:${id}`, {
        first_name,
        id,
        second_name,
        avatar,
        email
    });
    
    console.log(`userid=${id} data saved... in the local storage`);
};

const User = ({userId}) => {
    const [userData, setUserData ] = useState();
    const [ error, setError ]= useState();
    const [loading, setLoading ] = useState(false);
    

    // memo 테스트용 로그
    useEffect( ()=> {
        console.log("User Component Rerendered");
    });

    // 로컬 스토리지 확인하여 없으면 API 호출 후, 해당 정보 저장
    useEffect( () => {
        if (!userId) return;

        const curUserData = getUserDataFromStorage(userId)

        // 로컬 스토리지에 있는 경우 해당 정보 출력
        if (curUserData) {
            setUserData(curUserData);
            return;
        }
        // 로컬 스토리지에 없는 경우 API 호출 및 정보 저장
        else {
            // API 호출 후 대기
            setLoading(true);

            fetch(`https://reqres.in/api/users/${userId}`)
                .then(res=>res.json())
                .then(res => {
                    const userData = res["data"];
                    saveUserDataToStorage(userData)
                    setUserData(userData);
                })
                .then(()=>setLoading(false))    // 호출 완료 후 대기상태 끔
                .catch( (e)=>{
                    setError(e);
                 });  // 에러 발생 시 에러 상태 업데이트             
        }
        

    }, [userId])
    

    // 로딩, 에러, 데이터 없는 경우에 대한 렌더링
    if (loading)
        return <h1>Loading...</h1>
    if (error) 
        return <pre>{error}</pre>;
    if (!userData)
        return null;

    return (
        <div className="User">
            <img 
                src = {userData.avatar}
                alt = {userData.first_name}
                style = {{width: 200}}
            />
            <div>
                <h1>{userData.first_name} {userData.second_name}</h1>
                {userData.email && <p>{userData.email}</p>}
            </div>
        </div>
    );
}

const PureUser = memo(User);

export default PureUser;