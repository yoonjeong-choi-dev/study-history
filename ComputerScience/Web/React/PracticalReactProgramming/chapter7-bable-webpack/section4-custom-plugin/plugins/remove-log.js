module.exports = function({types: t}) {
  return {
    visitor: {
      // console.log 코드에 해당하는 노드 타입
      ExpressionStatement(path) {
        // 해당 노드의 expression 속성이 CallExpression(함수 호출 코드)인지 확인
        if(t.isCallExpression(path.node.expression)) {
          // 해당 노드의 메서드 이름을 추출하여 console.log인지 확인
          const memberExp = path.node.expression.callee;

          // console.log이면, 해당 경로 삭제 i.e console.log 메서드 호출 부분 삭제
          if (
            memberExp.object.name === 'console' &&
            memberExp.property.name === 'log'
          ) {
            path.remove();
          }
        }
      }
    }
  }
}