const utils = (function() {
    const displayTime = (timestamp) => {

        // 두자리 수 포멧 : 자리수가 하나이면 앞에 0을 붙임
        const addZero = (num) => {
            return (num > 9 ? '' : '0') + num;
        }


        let today = new Date();
        let gap = today.getTime() - timestamp;

        const dateObj = new Date(timestamp);



        if(gap < (1000 * 60 * 60 * 24)) {
            // 현재 일에 해당하면 시/분/초
            return [
                addZero(dateObj.getHours()), ':',
                addZero(dateObj.getMinutes()), ':',
                addZero(dateObj.getSeconds())
            ].join('');
        } else {
            // 이전 날짜에 해당하면 년/원/일
            return [
                dateObj.getFullYear(), '/',
                addZero(dateObj.getMonth() + 1), '/',
                addZero(dateObj.getDate())
            ].join('');
        }
    }

    return {
        displayTime
    };
})();