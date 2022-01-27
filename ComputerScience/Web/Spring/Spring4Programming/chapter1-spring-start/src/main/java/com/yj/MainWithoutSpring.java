package com.yj;

import java.util.ArrayList;
import java.util.List;

public class MainWithoutSpring {
    public static void main(String[] args) {
        MavenBuildRunner buildRunner = new MavenBuildRunner();
        buildRunner.setMavenPath("/home/yjchoi/workspace");

        Project sampleProject = new Project();

        List<String> srcDirs = new ArrayList<String>();
        srcDirs.add("src");
        srcDirs.add("srcResources");

        sampleProject.setBinDir("bin");
        sampleProject.setSrcDirs(srcDirs);
        sampleProject.setBuildRunner(buildRunner);

        sampleProject.build();
    }
}
