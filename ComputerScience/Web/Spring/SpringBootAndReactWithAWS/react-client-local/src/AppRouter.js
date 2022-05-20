import React from "react";
import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import "./index.css";

import { Box } from "@material-ui/core";
import { Typography } from "@material-ui/core";

import TodoPage from "./page/TodoPage";
import Login from "./component/auth/Login";
import SignUp from "./component/auth/SignUp";

const CopyRight = () => {
  return (
    <Typography variant="body2" color="textSecondary" align="center">
      {"Copyright © "}
      yoonjeong-choi-dev, {new Date().getFullYear()}
      {"."}
    </Typography>
  );
};

const AppRouter = () => {
  return (
    <div>
      <Router>
        <div>
          <Routes>
            <Route exact path="/" element={<TodoPage />} />
            <Route excat path="/login" element={<Login />} />
            <Route exact path="/signup" element={<SignUp />} />
          </Routes>
        </div>
        <Box mt={5}>
          <CopyRight />
        </Box>
      </Router>
    </div>
  )
};

export default AppRouter