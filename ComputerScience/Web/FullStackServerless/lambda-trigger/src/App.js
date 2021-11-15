import React from "react";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Main from "./Main";
import AuthForm from "./AuthForm";
import S3ImageUpload from "./S3ImageUpload";

function App() {
  return (
    <BrowserRouter>
        <Routes>
            <Route exact path="/" element={<Main />} />
            <Route exact path="/auth" element={<AuthForm />} />
            <Route exact path="/s3" element={<S3ImageUpload/>} />
            <Route path="*" element={<Main />} />
        </Routes>
    </BrowserRouter>
);
}

export default App;
