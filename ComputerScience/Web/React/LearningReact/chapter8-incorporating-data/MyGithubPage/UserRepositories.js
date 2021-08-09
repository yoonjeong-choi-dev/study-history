import React from "react";
import Fetch from "./Fetch";
import RepositoryMenu from "./RepositoryMenu";



const UserRepositories = ({login, repo, onSelect=f=>f}) => {
    return (
        <Fetch
            uri={`https://api.github.com/users/${login}/repos`}
            renderSuccess= {({data}) => (
                <RepositoryMenu
                    respositories={data}
                    selectedRepo = {repo}
                    onSelect={onSelect}
                />
            )}
        />
    )
}

export default UserRepositories;