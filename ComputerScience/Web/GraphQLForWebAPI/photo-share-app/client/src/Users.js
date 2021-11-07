import React from 'react';
import { Query, Mutation } from "react-apollo";
import { gql } from 'apollo-boost'
import { ROOT_QUERY } from "./App";

// 캐시 정책 : 캐시 데이터 사용 및 항상 네트워크를 통해 캐시 업데이트
const Users = () => {
    return (
        <Query query={ROOT_QUERY} fetchPolicy="cache-and-network">
            {
                ({ data, loading, refetch }) => loading ?
                    <p>Load Users ...</p> :
                    <UserList
                        count={data.totalUsers}
                        users={data.allUsers}
                        refetchUsers={refetch}
                    />
            }
        </Query>
    )
};


const UserList = ({ count, users, refetchUsers }) => {
    return (
        <div>
            <p>{count} Users</p>
            <button onClick={() => refetchUsers()}>다시 가져오기</button>
            <AddFakeUserButton count={1} />
            <DelteAllFakeUserButton />
            <ul>
                {users.map(user => 
                    < UserListItem
                        key={user.githubLogin}
                        name={user.name}
                        avatar={user.avatar}
                        githubLogin={user.githubLogin}
                    />
                )}
            </ul>
        </div>

    )
}

const UserListItem = ({ name, avatar, githubLogin }) => {
    return (
        <li>
            <img src={avatar} width={48} height={48} alt={avatar} />
            <p> Name : {name}</p>
            <p> Github : {githubLogin} </p>
        </li>
    )
}

// mutation AST to add fake users
const ADD_FAKE_USERS_MUTATION = gql `
    mutation addFakeUsers($count: Int!) {
        addFakeUsers(count: $count) {
            githubLogin
            name
            avatar
        }
    }
`

// mutation 반환 값인 생성된 유저만 알고 있으면 굳이 쿼리를 요청할 필요가 없음
// 쿼리 요청 대신, 생성된 유저를 캐시에 업데이트는 방식으로 변경
// => 불필요한 쿼리 요청 없어짐
const updateUserCache = ( cache, { data:{ addFakeUsers } }) => {
    let data = cache.readQuery({ query: ROOT_QUERY })
    data.totalUsers += addFakeUsers.length
    data.allUsers = [
        ...data.allUsers,
        ...addFakeUsers
    ]

    cache.writeQuery({ query: ROOT_QUERY, data })
}    

const AddFakeUserButton = ({count}) => {
    return (
        <Mutation 
            mutation={ADD_FAKE_USERS_MUTATION} 
            update={updateUserCache}
            variables={ { count : count }} >
            { addFakeUsers => <button onClick={addFakeUsers}>임시 사용자 추가</button> }
        </Mutation>
    )
}

const DELETE_ALL_FAKE_USERS = gql `
    mutation deleteFakeUsers {
        deleteAllFakeUsers
    }
`

const DelteAllFakeUserButton = () => {
    return (
        <Mutation
            mutation={DELETE_ALL_FAKE_USERS} 
            refetchQueries={ [ {query: ROOT_QUERY}]}
        >
            { deleteAllFakeUsers => <button onClick={deleteAllFakeUsers}>임시 사용자 삭제</button>}
        </Mutation>
    )
}

export default Users;