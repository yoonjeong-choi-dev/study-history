package com.yj.beanfactory;

import org.springframework.beans.BeansException;
import org.springframework.beans.FatalBeanException;
import org.springframework.beans.MutablePropertyValues;
import org.springframework.beans.factory.config.BeanDefinition;
import org.springframework.beans.factory.config.BeanFactoryPostProcessor;
import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;

public class ThresholdRequiredBeanFactoryPostProcessor implements BeanFactoryPostProcessor {

    private int defaultThreshold;

    public void setDefaultThreshold(int defaultThreshold) {
        this.defaultThreshold = defaultThreshold;
    }

    @Override
    public void postProcessBeanFactory(ConfigurableListableBeanFactory beanFactory) throws BeansException {
        // 빈 팩터리에 있는 빈들의 이름들
        String[] beanNames = beanFactory.getBeanDefinitionNames();
        for(String name : beanNames) {
            // 빈의 설정 정보
            BeanDefinition beanDef = beanFactory.getBeanDefinition(name);
            Class<?> klass = getClassFromBeanDef(beanDef);

            // 빈의 클래스가 ThresholdRequired 인터페이스 참조 변수에 할당 가능한 경우
            // i.e threshold setter가 있는 경우
            if(klass != null && ThresholdRequired.class.isAssignableFrom(klass)) {
                MutablePropertyValues prop = beanDef.getPropertyValues();

                // 해당 빈의 threshold 프로퍼티가 없는 경우 디폴트값 설정
                if(!prop.contains("threshold")) {
                    prop.add("threshold", defaultThreshold);
                }
            }
        }
    }

    private Class<?> getClassFromBeanDef(BeanDefinition beanDef) {
        if (beanDef.getBeanClassName() == null) return  null;

        try {
            // 빈의 설정정보에서 빈의 클래스 이름을 이용하여 클래스 자체 반환
            return Class.forName(beanDef.getBeanClassName());
        } catch (ClassNotFoundException ex) {
            throw new FatalBeanException(ex.getMessage(), ex);
        }
    }
}
