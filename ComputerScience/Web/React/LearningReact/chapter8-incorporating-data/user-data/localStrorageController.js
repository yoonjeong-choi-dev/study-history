export function loadJSONFromStorage(key) { 
    return key && JSON.parse(localStorage.getItem(key));
}

export function saveJSONToStorage(key, data) {
    localStorage.setItem(key, JSON.stringify(data));
}