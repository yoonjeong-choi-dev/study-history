import React from "react";
import { Link,useLocation, Outlet } from "react-router-dom";

export function Home() {
    return(
        <div>
            <h1>[Home Page]</h1>
            <nav>
                <Link to="about">회사 소개</Link>
                <Link to="events">이벤트</Link>
                <Link to="products">제품</Link>
                <Link to="contact">고객 지원</Link>
            </nav>
        </div>
    );
}

export function About() {
    // Outlet : 하위 경로 컴포넌트 표시
    return (
        <div>
            <h1>[회사 소개]</h1>
            <Outlet/>   
        </div>
    );
}

export function Services() {
    return (
      <section>
        <h2>About Services</h2>
        <p>
          우리 회사 서비스
        </p>
      </section>
    );
  }
  export function History() {
    return (
      <section>
        <h2>About History</h2>
        <p>
          우리 회사 역사
        </p>
      </section>
    );
  }
  export function Location() {
    return (
      <section>
        <h2>About Location</h2>
        <p>
          우리 회사 위치
        </p>
      </section>
    );
  }

export function Events() {
    return (
        <div>
            <h1>[이벤트]</h1>
        </div>
    );
}

export function Products() {
    return (
        <div>
            <h1>[제품]</h1>
        </div>
    );
}

export function Contact() {
    return (
        <div>
            <h1>[고객지원]</h1>
        </div>
    );
}

export function WRONG404() {
    let location = useLocation();

    return (
        <div>
            <h1>404 - Resource not found</h1>
            <h2>At {location.pathname}</h2>
        </div>
    )
}