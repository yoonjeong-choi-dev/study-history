package com.yj.domain;

import lombok.Getter;
import lombok.ToString;

@Getter
@ToString
public class PageDTO {
    private int perPages = 10;   // 현재 보여줘야 할 페이지 리스트의 길이
    private int startPage;  // 현재 보여줘야 할 페이지 리스트의 첫 페이지 번호
    private int endPage;    // 현재 보여줘야 할 페이지 리스트의 끝 페이지 번호
    private boolean prev, next; // 이전과 다음으로 이동 가능한 링크 표시 여부

    private int total;  // 전체 데이터 개수
    private PageCriteria cri;

    public PageDTO(PageCriteria cri, int total) {
        this.cri = cri;
        this.total = total;

        // 소수점 올림 처리를 이용하여 현재 페이지에서 페이지 리스트의 마지막 페이지 계산
        this.endPage = (int) (Math.ceil((double)cri.getPageNum() / (double)this.perPages )) * this.perPages;
        this.startPage = this.endPage - this.perPages + 1;

        // 소수점 올림 처리를 이용하여 전체 컨텐츠 개수를 표현하기 위한 페이지 전체 개수 계산
        int realEndPage = (int) (Math.ceil((double) this.total / (double)cri.getNumContents()));
        if ( realEndPage < this.endPage ) {
            this.endPage = realEndPage;
        }

        this.prev = this.startPage > 1;
        this.next = this.endPage < realEndPage;
    }
}
