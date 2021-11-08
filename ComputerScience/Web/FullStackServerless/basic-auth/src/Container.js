// 다른 컴포넌트의 스타일링을 위한 래퍼 컴포넌트

import React from "react";

const styles = {
    container: {
        margin: "0 auto",
        padding: "50px 100px"
    }
};

const Container = ({ children }) => {
    return (
        <div style={styles.container}>
            {children}
        </div>
    )
};

export default Container;