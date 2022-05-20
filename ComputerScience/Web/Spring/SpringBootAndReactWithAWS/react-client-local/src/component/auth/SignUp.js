import React from "react";
import { Button, TextField, Link, Grid, Container, Typography } from "@material-ui/core";

import { signup } from "../../shared/APIService";

const SignUp = (props) => {
  const onEventSubmit = (e) => {
    e.preventDefault();

    const data = new FormData(e.target);
    const email = data.get('email');
    const password = data.get('password');
    const username = data.get('username');

    if(!email || !password || !username) {
      alert("You must enter your email, password and username!");
      return;
    }

    signup({email, password, username})
      .then((res) => {
        // 가입 성공 시 로그인 페이지로 리다이렉트
        window.location.href = '/login';
      })
      .catch(err => {
          console.log(err);
      });
  };

  return (
    <Container component="main" maxWidth="xs" style={{ marginTop: "8%" }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <Typography component={'h1'} variant={'h5'}>
            회원 가입
          </Typography>
        </Grid>
      </Grid>

      <form noValidate onSubmit={onEventSubmit}>
        {" "}

        {/* email */}
        <Grid container spacing={2}>
          <Grid item xs={12}>
            <TextField variant="outlined" required fullWidth
              id="email" label="이메일" name="email" autoComplete="email" />
          </Grid>

          {/* password */}
          <Grid item xs={12}>
            <TextField type="password" variant="outlined" required fullWidth
              id="password" label="비밀번호" name="password" autoComplete="current-password" />
          </Grid>

          {/* username */}
          <Grid item xs={12}>
            <TextField variant="outlined" required fullWidth
              id="username" label="이름" name="username" autoComplete="fname" />
          </Grid>

          {/* submit */}
          <Grid item xs={12}>
            <Button type="submit" fullWidth variant="contained" color="primary">
              회원 가입
            </Button>
          </Grid>      
        </Grid>
      </form>

      <Grid container justifyContent="flex-end">
        <Link href="/login" variant="body2">
          이미 계정이 있으십니까? 로그인하세요.
        </Link>
      </Grid>

    </Container>
  );
};

export default SignUp;