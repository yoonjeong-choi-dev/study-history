import React, { Component, Fragment } from "react";
import { BrowserRouter, Switch, Route } from "react-router-dom";
import { gql } from "apollo-boost";
import { withApollo } from "react-apollo";

import Users from "./Users";
import AuthorizedUser from "./AuthorizedUser";
import Photos from "./Photos";
import PostPhoto from "./PostPhoto";


// 다른 컴포넌트에서 재사용하기 위한 편의 루트 쿼리
// 해당 데이터를 캐싱
export const ROOT_QUERY = gql`
  query allUsers { 
    totalUsers
    totalPhotos
    allUsers { ...userInfo }
    me { ...userInfo}
    allPhotos {
      id
      name
      category
      created
      url
      description
    }
  }

  fragment userInfo on User {
    githubLogin
    name
    avatar
  }
`

// 서브스크립션 쿼리 정의
const LISTEN_FOR_USERS = gql`
    subscription {
        newUser {
            githubLogin
            name
            avatar
        }
    }
`

const LISTEN_FOR_PHOTOS = gql`
    subscription {
        newPhoto {
            id
            name
            url
            postedBy {
              name
            }
        }
    }
`

class App extends Component {
  componentDidMount() {
    let { client } = this.props;

    // 이벤트 리스너 설정
    this.listenForUsers = client
      .subscribe({ query: LISTEN_FOR_USERS })
      .subscribe(({ data: { newUser } }) => {
        // 로컬 캐시에 저장
        const data = client.readQuery({ query: ROOT_QUERY })
        data.totalUsers += 1
        data.allUsers = [
          ...data.allUsers,
          newUser
        ]
        client.writeQuery({ query: ROOT_QUERY, data })
      })

    this.listenForPhotos = client
      .subscribe({ query: LISTEN_FOR_PHOTOS })
      .subscribe(({ data: { newPhoto } }) => {
        // 로컬 캐시에 저장
        const data = client.readQuery({ query: ROOT_QUERY })
        data.totalPhotos += 1
        data.allPhotos = [
          ...data.allPhotos,
          newPhoto
        ]
        client.writeQuery({ query: ROOT_QUERY, data })
      })

    console.log(client)
  }

  // 마운트 해제 시, 소식 듣기를 중단
  componentWillUnmount() {
    this.listenForUsers.unsubscribe()
    this.listenForPhotos.unsubscribe()
  }

  render() {
    return (
      <BrowserRouter>
          <Switch>
            <Route exact path="/" component={() =>
              <Fragment>
                <h1>Photo Sharing App Client</h1>
                <AuthorizedUser />
                <Users />
                <Photos />
              </Fragment>
            } />
            <Route path="/newPhoto" component={PostPhoto} />
            <Route component={({ location }) => <h1>"{location.pathname}" not found</h1>} />
          </Switch>
      </BrowserRouter>
    )
  }
}


export default withApollo(App)