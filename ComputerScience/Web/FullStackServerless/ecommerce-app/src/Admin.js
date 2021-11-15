// 새 항목을 생성하는 양식
// withAuthenticator를 이용하여 로그인 여부 확인

import React, { useState } from "react";
import { Input, Button } from "antd";
import { API } from "aws-amplify"
import { withAuthenticator } from "@aws-amplify/ui-react";

const containerStyle = {
    width: 400,
    margin: "20px auto"
};

const inputStyle = {
    marginTop: "10px"
};

const buttonStyle = {
    marginTop: "10px"
};

const initialState = {
    name: "",
    price: ""
};

const Admin = () => {
    const [itemInfo, updateItemInfo] = useState(initialState);

    const updateForm = (e) => {
        const formData = {
            ...itemInfo,
            [e.target.name]: e.target.value
        };
        updateItemInfo(formData);
    }

    const addItem = async () => {
        try {
            if (!itemInfo.name || !itemInfo.price) {
                alert("Please enter name and price!");
                return;
            }
            const price = parseInt(itemInfo.price);
            if (!price) {
                alert("Please enter valid price(must be integer)!");
                return;
            }

            const data = {
                body: {
                    ...itemInfo,
                    price: price
                }
            };

            updateItemInfo(initialState);
            await API.post("ecommerceAPI", "/products", data);
        } catch (err) {
            console.error("Fail to add an item : ", err);
        }
    }

    return (
        <div style={containerStyle}>
            <Input
                name="name"
                onChange={updateForm}
                value={itemInfo.name}
                style={inputStyle}
                placeholder="Item name"
            />
            <Input
                name="price"
                onChange={updateForm}
                value={itemInfo.price}
                style={inputStyle}
                placeholder="Item price"
            />
            <Button
                style={buttonStyle}
                onClick={addItem}
            >Add Product</Button>
        </div>
    );
};

export default withAuthenticator(Admin);