import React from "react";
import Fetch from "./Fetch";
import RepositoryMenu from "./RepositoryMenu";



const UserRepositories = ({login, selectedRepo, onSelect=f=>f}) => {
    const repoDetails = ({data}) => {
        return (
            <RepositoryMenu
                login={login}
                respositories={data}
                selectedRepo = {selectedRepo}
                onSelect={onSelect}
            />
        )
    }

    return (
        <Fetch
            uri={`https://api.github.com/users/${login}/repos`}
            renderSuccess={repoDetails}
        />
    )
}

export default UserRepositories;