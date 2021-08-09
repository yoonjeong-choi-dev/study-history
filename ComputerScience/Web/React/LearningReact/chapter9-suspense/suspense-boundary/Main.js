import React from "react";
import SiteLayout from "./SiteLayout";
import ErrorBoundary, {ErrorScreen} from "./ErrorBoundary";

import "./error.css";


const Menu = ()=> {
    return (
        <ErrorBoundary fallback={ErrorScreen}>
            <h1 style={{ color: "Blue" }}>TODO: Build Menu</h1>
        </ErrorBoundary>
    )
}

const Callout = ({children}) => {
    return (
        <ErrorBoundary fallback={ErrorScreen}>
            <div className="callout">{children}</div>
        </ErrorBoundary>
    )
}

const Content = ({children}) => {
    return (
        <ErrorBoundary fallback={ErrorScreen}>
                <div style={{border: "2px solid", margin: "10px"}}>
                    {children}
                    <h3>Content</h3>
                    <p>This is the main content</p>
            </div>
        </ErrorBoundary>
    )
}

const Main = () => {
    return (
        <SiteLayout menu={<Menu/>}>
            <Callout>
                <Content>
                    <h1>Welcom to the Site!</h1>
                </Content>
            </Callout>
        </SiteLayout>
    )
}

export default Main;