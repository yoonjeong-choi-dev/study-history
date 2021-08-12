import './App.css';
import React from "react";
import {Route, Routes, useRoutes} from "react-router-dom";

import {
  Home,
  About,
  Services,
  History,
  Location,
  Events,
  Products,
  Contact,
  WRONG404
} from "./Pages";

function AppLegacy() {
  return (
    <div className="App">
      <Routes>
        <Route path="/" element={<Home/>}/>
        <Route path="about" element={<About/>}>
          <Route path="services" element={<Services/>}/>
          <Route path="history" element={<History/>}/>
          <Route path="location" element={<Location/>}/>
        </Route>
        <Route path="events" element={<Events/>}/>
        <Route path="products" element={<Products/>}/>
        <Route path="contact" element={<Contact/>}/>
        <Route path="*" element={<WRONG404/>}/>
      </Routes>
    </div>
  );
}

function App() {
  let element = useRoutes([
    { path: "/", element: <Home /> },
    {
      path: "about",
      element: <About />,
      children: [
        {
          path: "services",
          element: <Services />
        },
        { path: "history", element: <History /> },
        {
          path: "location",
          element: <Location />
        }
      ]
    },
    { path: "events", element: <Events /> },
    { path: "products", element: <Products /> },
    { path: "contact", element: <Contact /> },
    { path: "*", element: <WRONG404 /> },
    {
      path: "services",
      redirectTo: "about/services"
    }
  ]);

  return element;
}

export default App;
