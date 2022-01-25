// const presets = [
//   [
//     '@babel/preset-env',
//     {
//       targets: {
//         chrome: '40', // 크롬 최소 40버전까지 지원
//       },
//       useBuiltIns: 'entry', // 폴리필 설정 : 지원하는 브라우저에서 필요한 폴리필만 포함(사용하지 않는 것포함)
//       corejs: {
//         version: 3,   // core-js 버전 정보
//         proposals: true,
//       }
//     }
//   ],
// ];

const presets = [
  [
    '@babel/preset-env',
    {
      targets: {
        chrome: '40', // 크롬 최소 40버전까지 지원
      },
      useBuiltIns: 'usage', // 폴리필 설정 : 지원하는 브라우저에서 필요한 폴리필만 포함
      corejs: {
        version: 3,   // core-js 버전 정보
        proposals: true,
      }
    }
  ],
];

module.exports = { presets };