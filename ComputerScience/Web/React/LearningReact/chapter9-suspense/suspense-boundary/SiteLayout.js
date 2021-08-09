import React from "react";

export default function SiteLayout({
    children,
    menu = c=>null
}) {
    return (
        <div className="site-container">
            <div>{menu}</div>
            <div>{children}</div>
        </div>
    )
};