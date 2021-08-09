import React from "react";
import SiteLayout from "./SiteLayout";
import ErrorBoundary from "./ErrorBoundary";

import "./error.css";

// 의도적으로 오류를 발생시키는 컴포넌트
const BreakThings = () => {
    throw new Error("We intentionally broke something!!");
}

const ErrorScreen = ({error}) =>{
    return (
        <div className="error">
            <h3>We are sorry.... something went wrong</h3>
            <p>We cannot process your request at this momemt.</p>
            <p>ERROR: {error.message} </p>
        </div>
    )
}

const Menu = ()=> {
    return (
        <p style={{ color: "Blue" }}>Menu</p>
    )
}

const Content = ({children}) => {
    return (
        <div style={{border: "2px solid", margin: "10px"}}>
            <h1>Content</h1>
            <p>This is the main part of the example layout</p>
            {children}
        </div>
    )
}

const Main = () => {
    return (
        <SiteLayout menu={
            <ErrorBoundary fallback={ErrorScreen}>
                <Menu/>
                <BreakThings/>
            </ErrorBoundary>
        }>
            <Content >
                <ErrorBoundary fallback={ErrorScreen}>
                    <BreakThings/>
                </ErrorBoundary>
            </Content>
            
            
        </SiteLayout>
    )
}

export default function ErrorBoundaryExamples(){
    return (
        <Main/>
    )
};