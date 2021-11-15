// 네비게이션 컴포넌트 : 각 페이지에 대한 링크 제공

import React, { useState, useEffect } from "react";
import { Link } from "react-router-dom";
import { Menu } from "antd";
import { HomeOutlined, ProfileOutlined, UserOutlined } from "@ant-design/icons";
import { Hub } from "aws-amplify";
import checkUser from "./checkUser";

const Nav = (props) => {
    const { current } = props;
    const [user, updateUser] = useState({});

    // 마운트 시, 로그인 여부 확인
    useEffect(() => {
        console.log("NAV : ", current);
        checkUser(updateUser);
        Hub.listen("auth", (data) => {
            const { payload: { event } } = data;
            console.log("Check User event : ", event);
            if (event === "signIn" || event === "signOut") {
                checkUser(updateUser);
            }
        })
    }, []);

    return (
        <div>
            <Menu selectedKeys={[current]} mode="horizontal">
                <Menu.Item key="home">
                    <Link to="/">
                        <HomeOutlined />Home
                    </Link>
                </Menu.Item>

                <Menu.Item key="profile">
                    <Link to="/profile">
                        <UserOutlined />Profile
                    </Link>
                </Menu.Item>
                {
                    user.isAdmin && (
                        <Menu.Item key="admin">
                            <Link to="/admin">
                                <ProfileOutlined />Admin
                            </Link>
                        </Menu.Item>
                    )
                }

            </Menu>
        </div>
    )
};

export default Nav;