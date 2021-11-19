import React, { useReducer, useEffect } from "react";
import { listPosts } from "./graphql/queries";
import { onCreatePost } from "./graphql/subscriptions";
import { API, graphqlOperation, Storage } from "aws-amplify";

const postContainer = { padding: "20px 0px 0px", borderBottom: "1px solid #ddd" };
const heading = { margin: "20px 0px" };
const postImage = { width: 400 };
const postTitle = { marginTop: 4 };

const reducer = (state, action) => {
    switch (action.type) {
        case "SET_POSTS":
            return action.posts;
        case "ADD_POST":
            return [action.post, ...state];
        default:
            return state;
    }
};

const getSignedPosts = async (posts) => {
    // graphql를 통해 얻은 사진의 key를 이용하여 S3에서 signed url 가져옴
    const signedPosts = await Promise.all(
        posts.map(async item => {
            const signedUrl = await Storage.get(item.imageKey)
            item.imageUrl = signedUrl
            return item
        })
    );

    return signedPosts;
}


const Posts = () => {
    const [posts, dispatch] = useReducer(reducer, []);

    const fetchPosts = async () => {
        const postData = await API.graphql(graphqlOperation(listPosts));
        const { data: { listPosts: { items } } } = postData;
        const signedPosts = await getSignedPosts(items);
        dispatch({ type: "SET_POSTS", posts: signedPosts });
    }

    // 사진 등록 서브스크립션 구독 및 데이터 패치
    useEffect(() => {
        fetchPosts();

        const subscription = API.graphql(graphqlOperation(onCreatePost))
            .subscribe({
                next: async post => {
                    const newPost = post.value.data.onCreatePost;
                    const signedUrl = await Storage.get(newPost.imageKey);
                    newPost.imageUrl = signedUrl;
                    dispatch({ type: "ADD_POST", post: newPost });
                }
            });

        return () => subscription.unsubscribe();
    }, []);

    return (
        <div>
            <h2 style={heading}>Posts</h2>
            {
                posts.map(post => (
                    <div key={post.id} style={postContainer}>
                        <img style={postImage} src={post.imageUrl} />
                        <h3 style={postTitle}>{post.title}</h3>
                    </div>
                ))
            }
        </div>
    )
};

export default Posts;