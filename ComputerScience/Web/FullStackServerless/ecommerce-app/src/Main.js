// 상품 항목을 렌더링하는 컴포넌트 : 전체 유저 접근 가능

import React, { useState, useEffect } from "react";
import Container from "./Container";
import { API } from "aws-amplify";
import { List } from "antd";
import checkUser from "./checkUser";

const Main = () => {
    const [state, setState] = useState({ products: [], loading: true });
    const [user, updateUser] = useState({});

    let didCancel = false;

    const getProducts = async () => {
        const data = await API.get("ecommerceAPI", "/products");
        console.log(data);

        if (didCancel) return;


        setState({
            products: data.data.Items,
            loading: false
        });
    };

    const deleteItem = async (id) => {
        const originState = { ...state }
        try {
            const products = state.products.filter(product => product.id !== id);
            setState({ ...state, products });

            await API.del("ecommerceAPI", { body: { id } });
            console.log("Success to delete");
        } catch (error) {
            console.error("Fail to delete : ", error);
            setState({ ...originState });
        }
    };


    useEffect(() => {
        getProducts();
        checkUser(updateUser);
        return () => didCancel = true;
    }, []);

    return (
        <Container>
            <List
                itemLayout="horizontal"
                dataSource={state.products}
                loading={state.loading}
                renderItem={item => (
                    <List.Item
                        actions={user.isAuthorized ?
                            [<p onClick={() => deleteItem(item.id)} key={item.id}>delete</p>] : null}
                    >
                        <List.Item.Meta
                            title={item.name}
                            description={item.price}
                        />
                    </List.Item>
                )}
            />
        </Container>
    );
}

export default Main;