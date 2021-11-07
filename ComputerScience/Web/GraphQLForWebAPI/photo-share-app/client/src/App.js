import React from 'react'
import Users from './Users'
import { BrowserRouter } from 'react-router-dom'
import AuthorizedUser from './AuthorizedUser'
import { gql } from 'apollo-boost'

// 다른 컴포넌트에서 재사용하기 위한 편의 루트 쿼리
// 해당 데이터를 캐싱
export const ROOT_QUERY = gql`
  query allUsers { 
    totalUsers
    allUsers { ...userInfo }
    me { ...userInfo}
  }

  fragment userInfo on User {
    githubLogin
    name
    avatar
  }
`

const App = () => 
  <BrowserRouter>
    <div>
      <h1>Photo Sharing App Client</h1>
      <AuthorizedUser />
      <Users/>
    </div>
  </BrowserRouter>  

export default App