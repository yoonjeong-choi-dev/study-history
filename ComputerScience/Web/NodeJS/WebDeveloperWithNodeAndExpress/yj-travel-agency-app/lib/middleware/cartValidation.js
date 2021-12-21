// 장바구니 관련 미들웨어 
module.exports = {

    resetValidation: (req, res, next) => {
        const { cart } = req.session;

        // 세션에 카트 정보가 있는 경우, 경고/에러 메시지 초기화
        if (cart) {
            cart.warnings = [];
            cart.errors = [];
        }

        next();
    },

    checkWaivers: (req, res, next) => {
        const { cart } = req.session;

        // 세션에 카트 정보가 없으면 다음 미들웨어로 넘어감
        if (!cart) return next();

        // Array.some : true인 요소가 있으면 참
        // waiver(책임면제동의서)가 있는 상품인 경우, 동의서를 요구하는 경고문 전달
        if (cart.items.some(item => item.product.requiresWaiver)) {
            cart.warnings.push('One or more of your selected tours requires a waiver.');
        }
        next();
    },

    checkGuestCount: (req, res, next) => {
        const { cart } = req.session;

        // 세션에 카트 정보가 없으면 다음 미들웨어로 넘어감
        if (!cart) return next();

        // 상품의 최대 인원 수보다 많은 인원이 예약한 경우 에러 메시지 전달
        if (cart.items.some(item => item.guests > item.product.maxGuests)) {
            cart.errors.push('One or more of your selected tours cannot accomodate the number of guests you have selected');
        }

        next();
    },
};