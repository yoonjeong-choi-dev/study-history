import React from "react";
import { Link } from "react-router-dom";

const footerStyle = {
    borderTop: "1px solid #ddd",
    display: "flex",
    alignItems: "center",
    padding: "20px"
};

const Footer = () => {
    return (
        <div style={footerStyle} >
            <Link to="/admin">
                Admins
            </Link>
        </div>
    );
};

export default Footer;