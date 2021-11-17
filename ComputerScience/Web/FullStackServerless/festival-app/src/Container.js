// 다른 컴포넌트의 스타일링을 위한 래퍼 컴포넌트

import React from "react";

const styles = {
    container: {
        padding: "30px 40px",
        width: "calc(100vh - 120px)"
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