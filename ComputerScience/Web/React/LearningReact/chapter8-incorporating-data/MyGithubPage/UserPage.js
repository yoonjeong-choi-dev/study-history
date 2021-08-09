import React, {useState} from "react";
import SearchForm from "./SearchForm";
import GithubUser from "./GithubUser";
import UserRepositories from "./UserRepositories";
import RepositoryReadMe from "./RepositoryReadMe";


const UserPage = () => {
    const [login, setLogin] = useState("yoonjeong-choi-dev");
    const [repo, setRepo] = useState("study-history");

    const handleSearch = login => {
        if (login) return setLogin(login);
        setLogin("")
        setRepo("");
    }

    if (!login)
        return <SearchForm onSearch={handleSearch}/>

    return (
        <>
            <SearchForm onSearch={handleSearch}/>
            {login && <GithubUser login={login} />}
            {login && (
                <UserRepositories
                    login={login}
                    repo={repo}
                    onSelect={setRepo}
                />
            )}
            {login && repo && (
                <RepositoryReadMe login={login} repo={repo} />
            )}
        </>
    );

}

export default UserPage;