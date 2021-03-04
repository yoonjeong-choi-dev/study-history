window.onload = init;
window.addEventListener("resize", onResize, false);

// Three.js 에서 필요한 필수 요소는 전역 처리
var scene;
var camera;
var renderer;


function onResize() {
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
    renderer.setSize(window.innerWidth, window.innerHeight);
}


function init() {
    var stats = initFrameStats();

    scene = new THREE.Scene();
    scene.fog = new THREE.Fog(0xaaaaaa, 0.010, 200);
    

    // 카메라 생성
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.set(20, 30, 21);
    camera.lookAt(new THREE.Vector3(0, 0, -30));
    scene.add(camera)

    // 복잡한 광원을 연산하기 위한 특수 렌더러 사용
    renderer = new THREE.WebGLDeferredRenderer({
        width: window.innerWidth,
        height: window.innerHeight,
        scale: 1,
        antialias: true,
        tonemapping: THREE.FilmicOperator,
        brightness: 2.5
    });

    // 바닥면 생성 : phong shader 사용
    var planeGeometry = new THREE.PlaneGeometry(70, 70, 1, 1);
    var planeMaterial = new THREE.MeshPhongMaterial({ 
        color: 0xffffff,
        specular: 0xffffff,
        shininess: 200
     });

    var plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.set(0, 0, 0);
    scene.add(plane);


    // 스포트라이트 광원 추가 : 보조 광원
    var spotLight0 = new THREE.SpotLight(0xcccccc);
    spotLight0.position.set(-40, 60, -10);
    spotLight0.intensity = 0.1;
    spotLight0.lookAt(plane);
    scene.add(spotLight0);

    // 면적 광원 1 & 발광 영역 1
    var areaLight1 = new THREE.AreaLight(0xff0000, 3);
    areaLight1.position.set(-10, 10, -35);
    areaLight1.rotation.set(-Math.PI/2, 0, 0);
    areaLight1.width = 4;
    areaLight1.height = 9.9;
    scene.add(areaLight1);

    var planeGeo1 = new THREE.BoxGeometry(4, 10, 0);
    var planeMat1 = new THREE.MeshBasicMaterial({ color: 0xff0000 });
    var plane1 = new THREE.Mesh(planeGeo1, planeMat1);
    plane1.position.copy(areaLight1.position);
    scene.add(plane1);

    // 면적 광원 2 & 발광 영역 2
    var areaLight2 = new THREE.AreaLight(0x00ff00, 3);
    areaLight2.position.set(0, 10, -35);
    areaLight2.rotation.set(-Math.PI / 2, 0, 0);
    areaLight2.width = 4;
    areaLight2.height = 9.9;
    scene.add(areaLight2);

    var planeGeo2 = new THREE.BoxGeometry(4, 10, 0);
    var planeMat2 = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
    var plane2 = new THREE.Mesh(planeGeo2, planeMat2);
    plane2.position.copy(areaLight2.position);
    scene.add(plane2);

    // 면적 광원 3 & 발광 영역 3
    var areaLight3 = new THREE.AreaLight(0x0000ff, 3);
    areaLight3.position.set(10, 10, -35);
    areaLight3.rotation.set(-Math.PI/2, 0, 0);
    areaLight3.width = 4;
    areaLight3.height = 9.9;
    scene.add(areaLight3);

    var planeGeo3 = new THREE.BoxGeometry(4, 10, 0);
    var planeMat3 = new THREE.MeshBasicMaterial({color: 0x0000ff});
    var plane3 = new THREE.Mesh(planeGeo3, planeMat3);
    plane3.position.copy(areaLight3.position);
    scene.add(plane3);


    
    document.getElementById("WebGL-output").appendChild(renderer.domElement);


    // 면적 광원들 조작하는 컨트롤러
    var controller = new function () {
        this.specular = 0xffffff;
        this.shininess = 200;
        this.color1 = 0xff0000;
        this.intensity1 = 2;
        this.color2 = 0x00ff00;
        this.intensity2 = 2;
        this.color3 = 0x0000ff;
        this.intensity3 = 2;
    }

    var gui = new dat.GUI();

    gui.addColor(controller, "specular").onChange((e)=>{
        planeMaterial = new THREE.MeshPhongMaterial({ 
            color: 0xffffff,
            specular: controller.specular,
            shininess: controller.shininess
         });
    
        plane = new THREE.Mesh(planeGeometry, planeMaterial);
        plane.rotation.x = -0.5 * Math.PI;
        plane.position.set(0, 0, 0);
        scene.add(plane);
    })

    gui.add(controller, "shininess", 0, 500).onChange((e)=>{
        planeMaterial = new THREE.MeshPhongMaterial({ 
            color: 0xffffff,
            specular: controller.specular,
            shininess: controller.shininess
         });
    
        plane = new THREE.Mesh(planeGeometry, planeMaterial);
        plane.rotation.x = -0.5 * Math.PI;
        plane.position.set(0, 0, 0);
        scene.add(plane);
    })

    gui.addColor(controller, "color1").onChange((e)=> {
        areaLight1.color = new THREE.Color(e);
        planeGeometry1Mat.color = new THREE.Color(e);
        scene.remove(plane1);
        plane1 = new THREE.Mesh(planeGeometry1, planeGeometry1Mat);
        plane1.position.copy(areaLight1.position);
        scene.add(plane1);

    });
    gui.add(controller, "intensity1", 0, 5).onChange((e)=> {
        areaLight1.intensity = e;
    });
    gui.addColor(controller, "color2").onChange((e)=> {
        areaLight2.color = new THREE.Color(e);
        planeGeometry2Mat.color = new THREE.Color(e);
        scene.remove(plane2);
        plane2 = new THREE.Mesh(planeGeometry2, planeGeometry2Mat);
        plane2.position.copy(areaLight2.position);
        scene.add(plane2);
    });
    gui.add(controller, "intensity2", 0, 5).onChange((e)=> {
        areaLight2.intensity = e;
    });
    gui.addColor(controller, "color3").onChange((e)=> {
        areaLight3.color = new THREE.Color(e);
        planeGeometry3Mat.color = new THREE.Color(e);
        scene.remove(plane3);
        plane3 = new THREE.Mesh(planeGeometry1, planeGeometry3Mat);
        plane3.position.copy(areaLight3.position);
        scene.add(plane3);
    });
    gui.add(controller, "intensity3", 0, 5).onChange((e)=> {
        areaLight3.intensity = e;
    });



    renderScene();


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

        requestAnimationFrame(renderScene);
        renderer.render(scene, camera);
    }

}