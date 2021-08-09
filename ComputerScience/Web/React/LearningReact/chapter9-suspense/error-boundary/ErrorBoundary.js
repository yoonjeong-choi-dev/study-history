import React, {Component} from "react";

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