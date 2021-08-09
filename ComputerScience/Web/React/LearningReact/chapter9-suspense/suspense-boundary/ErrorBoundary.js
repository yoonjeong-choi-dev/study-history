import React, {Component} from "react";

const ErrorScreen = ({error}) =>{
    return (
        <div className="error">
            <h3>We are sorry.... something went wrong</h3>
            <p>We cannot process your request at this momemt.</p>
            <p>ERROR: {error.message} </p>
        </div>
    )
}

export {ErrorScreen};

export default class ErrorBoundary extends Component {
    constructor(props) {
        super(props);
        this.state = {error:null};
    }
    

    static getDerivedStateFromError(error) {
        return {error};
    }

    render() {
        const {error} = this.state;
        
        if (error) return <this.props.fallback error={this.state.error} />;
        return this.props.children;
    }
}