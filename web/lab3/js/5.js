(function() {
    const landscapesCarouselElement = document.querySelector("#landscapes-carousel");
    const landscapesCarousel = new Carousel(landscapesCarouselElement, {
        pauseTime: 3000,
    });

    landscapesCarousel.play();

    const landscapesCarouselNext = document.querySelector("#landscapes-carousel-next");
    landscapesCarouselNext.addEventListener("click", () => {
        landscapesCarousel.next();
    });

    const landscapesCarouselPrev = document.querySelector("#landscapes-carousel-prev");
    landscapesCarouselPrev.addEventListener("click", () => {
        landscapesCarousel.prev();
    });
})();
