window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;

// Step 7 : resize
function onResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init() {
    var stats = initFrameStats();

    scene = new THREE.Scene();
    

    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(120, 60, 180);
    camera.lookAt(scene.position);
    scene.add(camera)

    // 렌더러 생성 
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);

    // 바닥면 생성
    var planeGeometry = new THREE.PlaneGeometry(180, 180);
    var planeMaterial = new THREE.MeshLambertMaterial({
        color: 0xffffff
    });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.set(0, 0, 0);
    scene.add(plane);

    // 물체 생성
    var cubeGeometry = new THREE.BoxGeometry(4,4,4);
    
    for(let j=0;j<planeGeometry.parameters.height/5; j++){
        for(let i=0;i<planeGeometry.parameters.width/5; i++){
            var rnd = Math.random()*0.75 + 0.25;
            var cubeMaterial = new THREE.MeshLambertMaterial();
            cubeMaterial.color = new THREE.Color(rnd, 0, 0);
            var cube = new THREE.Mesh(cubeGeometry, cubeMaterial);

            cube.position.z = -(planeGeometry.parameters.height/2) + 2 + (j*5);
            cube.position.x = -(planeGeometry.parameters.width/2) + 2 + (i*5);
            cube.position.y = 2;

            scene.add(cube);
        }
    }

    // 방향성 광원 추가
    var directionalLight = new THREE.DirectionalLight(0xffffff, 0.7);
    directionalLight.position.set(-20, 40, 60);
    scene.add(directionalLight);

    // 주변광 추가
    var ambientLight = new THREE.AmbientLight(0x292929);
    scene.add(ambientLight);

    document.getElementById("WebGL-output").appendChild(renderer.domElement);

    // 카메라 시점 물체
    var lookAtGeo = new THREE.SphereGeometry(2);
    var lookAtMesh = new THREE.Mesh(lookAtGeo, new THREE.MeshLambertMaterial({color: 0xff0000}));
    scene.add(lookAtMesh);
    lookAtMesh.visible = false;

    // 카메라 투상 방식을 조작하는 컨트롤러
    var isAnimating = false;
    var controller = new function(){
        this.perspective = "Perspective";
        this.switchCamera = function () {
            if(camera instanceof THREE.PerspectiveCamera){
                // 정사 투영
                camera = new THREE.OrthographicCamera(window.innerWidth/-16,  window.innerWidth / 16, window.innerHeight / 16, window.innerHeight / -16, -200, 500);
                camera.position.set(120, 60, 180);
                camera.lookAt(scene.position);
                this.perspective = "Otrhographic";
            }else{
                // 원근 투영
                camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
                camera.position.set(120, 60, 180);
                camera.lookAt(scene.position);
                this.perspective = "Perspective";
            }
        }

        this.toggleAnimate = function (){
            isAnimating = !isAnimating;
            lookAtMesh.visible = isAnimating;
        }
    }

    var gui = new dat.GUI();
    gui.add(controller, "switchCamera");
    gui.add(controller, "perspective").listen();
    gui.add(controller, "toggleAnimate");



    renderScene();


    var step = 0;
    // 프레임 확인 함수
    function initFrameStats() {
        var stats = new Stats();
        stats.setMode(0);   // 0: 프레임 확인용
        stats.domElement.style.position = "absolute";
        stats.domElement.style.left = "0px";
        stats.domElement.style.top = "0px";
        document.getElementById("Stats-output").appendChild(stats.domElement);

        return stats;
    }

    // 렌더링 처리 함수
    function renderScene() {
        // 통계치 업데이트
        stats.update();

        // 애니메이션 효과
        if(isAnimating){
            step +=0.02;
            if(camera instanceof THREE.Camera){
                var x = 10 + (100 * Math.sin(step));
                camera.lookAt(new THREE.Vector3(x, 10, 0));
                lookAtMesh.position.copy(new THREE.Vector3(x, 10 ,0));
            }
        }

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}