<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<%@include file="../includes/header.jsp" %>


<div class="row">
  <div class="col-md-4 col-md-offset-4">
    <div class="login-panel panel panel-default">
      <div class="panel-heading">
        <h3 class="panel-title">Logout Page</h3>
      </div>
      <div class="panel-body">
        <form role="form" method='post' action="/auth/customLogout">
          <fieldset>
            <a href="#" class="btn btn-lg btn-success btn-block">Logout</a>
          </fieldset>
          <input type="hidden" name="${_csrf.parameterName}" value="${_csrf.token}" />
        </form>
      </div>
    </div>
  </div>
</div>


<script>
    document.querySelector(".btn-success").addEventListener("click", (e) => {
        e.preventDefault();
        document.querySelector("form").submit();
    });
</script>

<c:if test="${param.logout != null}">
  <script>
      $(document).ready(function () {
          alert("로그아웃하였습니다.");
      });
  </script>
</c:if>

<%@include file="../includes/footer.jsp" %>
