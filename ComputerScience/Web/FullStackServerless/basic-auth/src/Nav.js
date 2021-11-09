// 네비게이션 컴포넌트 : 각 페이지에 대한 링크 제공

import React from "react";
import { Link } from "react-router-dom";
import { Menu } from "antd";
import { HomeOutlined, ProfileOutlined, FileProtectOutlined } from "@ant-design/icons";

const Nav = (props) => {
    // 현재 경로 이름 : Router에서 전달
    const { current } = props;

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
                        <ProfileOutlined />Profile
                    </Link>
                </Menu.Item>

                <Menu.Item key="protected">
                    <Link to="/protected">
                        <FileProtectOutlined />Protected
                    </Link>
                </Menu.Item>
            </Menu>
        </div>
    )
};

export default Nav;