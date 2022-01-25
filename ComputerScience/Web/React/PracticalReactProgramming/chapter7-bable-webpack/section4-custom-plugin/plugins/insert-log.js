module.exports = function({types: t}) {
  return {
    visitor: {
      // 함수 정의 노드에 대한 플러그인
      FunctionDeclaration(path) {
        // 함수 이름이 on으로 시작하는 경우
        if(path.node.id.name.substr(0,2) === 'on') {
          // 함수 body를 표현하는 배열의 맨 앞쪽에 로그 노드 추가
          path
            .get('body')
            .unshiftContainer(
              'body',
              // 아래 코드는 console.log를 AST 표현한 것
              t.expressionStatement(
                t.callExpression(
                  t.memberExpression(
                    t.identifier('console'),
                    t.identifier('log'),
                  ),
                  [t.stringLiteral(`on LOG : call ${path.node.id.name}`)],
                )
              )
            )
        }
      }
    }
  }
}