import React, {Component} from "react";
import { withRouter } from "react-router-dom";
import { Mutation } from "react-apollo";
import { gql } from "apollo-boost";
import { ROOT_QUERY } from "./App";

const POST_PHOTO_MUTATION = gql`
    mutation postPhoto($input: PostPhotoInput!) {
        postPhoto(input:$input) {
            id
            name
            url
        }
    }
`

const updatePhotoCache = ( cache, { data:{ postPhoto } }) => {
    let data = cache.readQuery({ query: ROOT_QUERY })
    data.allPhotos = [
        ...data.allPhotos,
        postPhoto
    ]

    cache.writeQuery({ query: ROOT_QUERY, data })
}    

class PostPhoto extends Component {
    // 사진 저장 시 필요한 파라미터들을 상태로 정의
    state = {
        name: "",
        description: "",
        category: "PORTRAIT",
        file: ""
    }

    // 현재 상태를 이용하여 사진 게시 요청
    postPhoto = async (mutation) => {
        await mutation ({
            variables: {
                input: this.state
            }
        }).catch(console.error);

        this.props.history.replace("/");
    }

    render() {
        return (
            <form onSubmit={e => e.preventDefault()}
                style={{
                    display: "flex",
                    flexDirection: "column",
                    justifyContent: "flex-start",
                    alignItems: "flex-start"
                }}>

                <h1>Post a Photo</h1>

                <input type="text"
                    style={{ margin: "10px" }}
                    placeholder="사진 이름"
                    value={this.state.name}
                    onChange={({target}) => this.setState({ name: target.value })} />
            
                <textarea type="text"
                    style={{ margin: "10px" }}
                    placeholder="사진 설명"
                    value={this.state.description}
                    onChange={({target}) => this.setState({ description: target.value })} />
            
                <select value={this.state.category} 
                    style={{ margin: "10px" }}
                    onChange={({target}) => this.setState({ category: target.value })}>
                    <option value="PORTRAIT">PORTRAIT</option>
                    <option value="LANDSCAPE">LANDSCAPE</option>
                    <option value="ACTION">ACTION</option>
                    <option value="GRAPHIC">GRAPHIC</option>
                </select>

                <input type="file"
                    style={{ margin: "10px" }}
                    accept=".png .jpg .jpeg"
                    onChange={({target}) => this.setState({
                        file: target.files && target.files.length ? target.files[0] : ""
                    })} />

                <div style={{ margin: "10px" }}>
                    <Mutation mutation={POST_PHOTO_MUTATION} update={updatePhotoCache}>
                        {mutation =>
                            <button onClick={() => this.postPhoto(mutation)}>
                                사진 게시
                            </button>
                        }    
                    </Mutation>
                    <button onClick={() => this.props.history.goBack()}>
                        취소
                    </button>
                </div>

            </form>
        )
    }

}


export default withRouter(PostPhoto);