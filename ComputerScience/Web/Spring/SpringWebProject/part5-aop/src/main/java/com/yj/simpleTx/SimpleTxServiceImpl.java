package com.yj.simpleTx;

import com.yj.simpleTx.mapper.TxTestMapper1;
import com.yj.simpleTx.mapper.TxTestMapper2;
import lombok.Setter;
import lombok.extern.log4j.Log4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

@Service
@Log4j
public class SimpleTxServiceImpl implements SimpleTxService {
    @Setter(onMethod_ = {@Autowired})
    private TxTestMapper1 mapper1;

    @Setter(onMethod_ = {@Autowired})
    private TxTestMapper2 mapper2;

    @Override
    public void addData(String value) {
        log.info("Start addData ==========================>");

        log.info("mapper1 insert ================");
        mapper1.insert(value);

        log.info("mapper2 insert ================");
        mapper2.insert(value);


        log.info("End addData <==========================");
    }

    @Transactional
    @Override
    public void addDataTx(String value) {
        log.info("Start addData With Transaction ==========================>");

        log.info("mapper1 insert ================");
        mapper1.insert(value);

        log.info("mapper2 insert ================");
        mapper2.insert(value);


        log.info("End addData <==========================");
    }
}
