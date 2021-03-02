window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;

// Step 7 : resize
function onResize(){
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init(){
    var stats = initFrameStats();

    scene = new THREE.Scene();
    //scene.fog = new THREE.Fog(0xfffff,  0.015, 100);
    
    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth/window.innerHeight, 0.1, 1000);
    camera.position.x = -30;
    camera.position.y = 40;
    camera.position.z = 30;
    camera.lookAt(scene.position)
    scene.add(camera)
    
    // 렌더러 생성 
    renderer = new THREE.WebGLRenderer();   
    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = true;

    // 바닥면 생성
    var planeGeometry = new THREE.PlaneGeometry(60, 40, 1, 1);
    var planeMaterial = new THREE.MeshLambertMaterial({
        color: 0xffffff
    });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5*Math.PI;
    plane.position.set(0, 0, 0);
    plane.receiveShadow = true;
    scene.add(plane);

    // 스포트라이트 추가
    var spotLight = new THREE.SpotLight(0xffffff);
    spotLight.position.set(-40, 60, -10);
    spotLight.castShadow = true;
    scene.add(spotLight);

    // 주변광 추가
    var ambientLight = new THREE.AmbientLight(0x0c0c0c);
    scene.add(ambientLight);
    
    document.getElementById("WebGL-output").appendChild(renderer.domElement);
    // UI controller 생성
    var controller = new function(){
        this.rotationSpeed = 0.02;
        this.numberOfObjects = scene.children.length;
        
        // 큐브 생성
        this.addCube = function () {

            // 큐브 생성 및 기본 설정
            let cubeSize = Math.ceil(Math.random()*3);
            let cubeGeometry = new THREE.BoxGeometry(cubeSize, cubeSize, cubeSize);
            let cubeMaterial = new THREE.MeshLambertMaterial({
                color: Math.random() * 0xffffff
            });
            let cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
            cube.castShadow = true;

            // name 추가
            // THREE.Scene.getObjectByName(name)을 통해 해당 객체에 접근 가능
            cube.name = "cube-" + this.numberOfObjects;

            // 큐브 transform 설정
            cube.position.x = -30 + Math.round(Math.random()*planeGeometry.parameters.width);
            cube.position.y = Math.round(Math.random() * 5);
            cube.position.z = -20 + Math.round(Math.random()*planeGeometry.parameters.height);
            scene.add(cube);
            this.numberOfObjects += 1;
        }

        // 큐브 제거
        this.removeCube = function(){
            let allChildren = scene.children;
            let lastObject = allChildren[allChildren.length-1];
            if(lastObject instanceof THREE.Mesh){
                scene.remove(lastObject);
                this.numberOfObjects -= 1;
            }
        }


        // 현재 장면의 모든 객체 출력
        this.printAllObjects = function(){
            console.log(scene.children);
        }
    }

    // UI controller와 연결시킬 GUI 설정
    let gui = new dat.GUI();
    gui.add(controller, 'rotationSpeed', 0, 0.5);
    gui.add(controller, 'addCube');
    gui.add(controller, 'removeCube');
    gui.add(controller, 'printAllObjects');
    gui.add(controller, 'numberOfObjects').listen();

    
    renderScene();

    

    // 프레임 확인 함수
    function initFrameStats(){
        var stats = new Stats();
        stats.setMode(0);   // 0: 프레임 확인용
        stats.domElement.style.position = "absolute";
        stats.domElement.style.left = "0px";
        stats.domElement.style.top = "0px";
        document.getElementById("Stats-output").appendChild(stats.domElement);

        return stats;
    }

    // 렌더링 처리 함수
    function renderScene(){
        // 통계치 업데이트
        stats.update();

        scene.traverse( (obj) => {
            if(obj instanceof THREE.Mesh && obj != plane){
                obj.rotation.x += controller.rotationSpeed;
                obj.rotation.y += controller.rotationSpeed;
                obj.rotation.z += controller.rotationSpeed;
            }
        })

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}