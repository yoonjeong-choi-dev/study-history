import React, { Component } from 'react';
import { withRouter } from 'react-router-dom';
import { Query, Mutation, withApollo, compose } from 'react-apollo';
import { ROOT_QUERY } from './App';
import { gql } from 'apollo-boost';

// 깃허브 인증 뮤테이션 : 토큰 반환
const GITHUB_AUTH_MUTATION = gql`
    mutation githubAuth($code:String!) {
        githubAuth(code:$code) { token }
    }
`;


// 로그인 및 로그아웃을 담당하는 컴포넌트
// 캐시 정책 : 캐시만 읽음 i.e 해당 컴포넌트에서는 쿼리 요청을 하지 않음
const Me = ({ logout, requestCode, signingIn }) => {
    return (
        <Query query={ROOT_QUERY} fetchPolicy="cache-only">
            {({ loading, data }) => data.me ?
                <CurrentUser {...data.me} logout={logout} /> :
                loading ?
                    <p>loading... </p> :
                    <button 
                        onClick={requestCode}
                        disabled={signingIn}>
                        깃허브로 로그인
                    </button>
            }
        </Query>

    )
}

const currentUserStyle = {
    border: "solid",
    padding: "10px",
    width: "50%"
}

// 로컬 스토리지에 저장된 인증 토큰을 이용하여 현재 사용자 정보 컴포넌트 정의
const CurrentUser = ({ name, avatar, githubLogin, logout }) => {
    return (
        <div style= {currentUserStyle}>
            <h2>[ Current Users ]</h2>
            <button onClick={logout}>로그아웃</button>
            <p>Name : {name}</p>
            <p>Github: {githubLogin} </p>
            <span>Avatar : </span><img src={avatar} width={48} height={48} alt="" />
            
        </div>
    )
}

class AuthorizedUser extends Component {
    // 인증이 된 경우에는 로그인 버튼 비활성화
    state = { signingIn: false }

    authorizationComplete = (cache, { data }) => {
        // 인증 토큰을 로컬 스토리지에 저장
        localStorage.setItem("token", data.githubAuth.token);

        // 토큰을 저장 후, 메인 페이지로 리다리엑트
        this.props.history.replace("/");
        this.setState({ signingIn: false });
    }

    // 해당 컴포넌트가 마운트될 때 실행 
    componentDidMount() {
        // 깃허브 로그인 후 리다익트 된 주소에서 code 얻어와서 인증 진행
        if (window.location.search.match(/code=/)) {
            // 인증 완료 상태 변경
            this.setState({ signingIn: true });

            // 깃허브에서 리다이렉트 된 주소에서 코드 값 가져오기
            const code = window.location.search.replace("?code=", "")

            // 인증 뮤테이션이 완료되면, 해당 함수 호출
            this.githubAuthMutation({ variables: { code } })
        }
    }

    // 로그아웃 버튼
    logout = () => {
        // 로컬 스토리지에서 토큰 삭제
        localStorage.removeItem('token');

        // 로컬 스토리지(캐시)에 현재 유저(me)를 null로 초기화
        let data = this.props.client.readQuery({ query: ROOT_QUERY });
        data.me = null;
        this.props.client.writeQuery({ query: ROOT_QUERY, data });
    }

    requestCode() {
        let clientID = process.env.REACT_APP_CLIENT_ID;

        // 깃허브 로그인 페이지로 리다이렉트
        window.location = `https://github.com/login/oauth/authorize?client_id=${clientID}&scope=user`;
    }

    render() {
        return (
            <Mutation mutation={GITHUB_AUTH_MUTATION}
                update={this.authorizationComplete}
                refetchQueries={[{ query: ROOT_QUERY }]}>
                {mutation => {
                    this.githubAuthMutation = mutation
                    return (
                        <Me signingIn={this.state.signingIn}
                            requestCode={this.requestCode}
                            logout={this.logout} />
                    )
                }}
            </Mutation>
        );
    }
}

export default compose(withApollo, withRouter)(AuthorizedUser)   ;