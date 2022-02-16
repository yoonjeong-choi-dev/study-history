<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags"%>

<sec:authorize access="isAnonymous()">
  <a href="<%request.getContextPath();%>/customLogin">Login</a>
</sec:authorize>

<sec:authorize access="isAuthenticated()">
  <h3>User Info</h3>
  <p>principal : <sec:authentication property="principal"/></p>
  <p>member vo : <sec:authentication property="principal.member"/></p>
  <p>name : <sec:authentication property="principal.member.userName"/></p>
  <p>Id : <sec:authentication property="principal.member.userId"/></p>
  <p>auth : <sec:authentication property="principal.member.authList"/></p>

  <a href="<%request.getContextPath();%>/customLogout">Logout</a>
</sec:authorize>