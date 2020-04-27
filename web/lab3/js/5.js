(function() {
    const landscapesCarouselElement = $("#landscapes-carousel");
    const landscapesCarousel = new Carousel(landscapesCarouselElement, {
        pauseTime: 3000,
    });

    landscapesCarousel.play();

    const landscapesCarouselNext = $("#landscapes-carousel-next");
    landscapesCarouselNext.click(() => {
        landscapesCarousel.next();
    });

    const landscapesCarouselPrev = $("#landscapes-carousel-prev");
    landscapesCarouselPrev.click(() => {
        landscapesCarousel.prev();
    });
})();
