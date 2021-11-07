import React from "react";
import { Query } from "react-apollo";
import { ROOT_QUERY } from "./App";


const photoStyle = {
    border: "solid",
    padding: "10px",
    width: "500px"
}
const Photo = ({url, id, name, description, category}) => {
    return (
        <div style={photoStyle}>
            <p>name : {name}</p>
            <p>description: {description} </p>
            <p>category: {category} </p>
            <img key={id} src={`http://localhost:4000${url}`} alt={name} width={350} />
        </div>
    )
}

const Photos = () => {
    return (
        <div>
            <h2> All Photos </h2>
            <Query query={ROOT_QUERY} >
                {
                    ({ data, loading }) => loading ?
                        <p>Load Photos... ...</p> :
                        data.allPhotos.map(photo => 
                            <Photo
                                key={photo.id} 
                                {...photo}
                            />
                        )

                }
            </Query>
        </div>
    )
}

export default Photos;