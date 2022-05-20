import React from "react";
import { signin } from "../../shared/APIService";
import { Container, Button, TextField, Grid, Typography, Link } from "@material-ui/core";

const Login = (props) => {
  const onEventSubmit = (e) => {
    e.preventDefault();

    const data = new FormData(e.target);
    const email = data.get('email');
    const password = data.get('password');

    if (!email || !password) {
      alert("You must enter your email and password!");
    } else {
      signin({ email, password });
    }
  }

  return (
    <Container component="main" maxWidth="xs" style={{ marginTop: "8%" }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <Typography component={'h1'} variant={'h5'}>
            로그인
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

          {/* submit */}
          <Grid item xs={12}>
            <Button type="submit" fullWidth variant="contained" color="primary">
              로그인
            </Button>
          </Grid>




        </Grid>
      </form>

      <Grid container justifyContent="flex-end">
        <Link href="/signup" variant="body2">
          <Grid item>계정이 없으시면, 회원가입을 하세요!</Grid>
        </Link>
      </Grid>
    </Container>
  )
}

export default Login;