class CarouselElementState {
    static HIDDEN = new CarouselElementState(null);
    static CURRENT = new CarouselElementState("current");
    static PREV = new CarouselElementState("prev");
    static NEXT = new CarouselElementState("next");

    constructor(className) {
        this.className = className;
    }
}

class CarouselElementTransition {
    static NONE = new CarouselElementTransition(null);
    static TRANSITION_CURRENT_TO_NEXT = new CarouselElementTransition("current-to-next");
    static TRANSITION_CURRENT_TO_PREV = new CarouselElementTransition("current-to-prev");
    static TRANSITION_NEXT_TO_CURRENT = new CarouselElementTransition("next-to-current");
    static TRANSITION_PREV_TO_CURRENT = new CarouselElementTransition("prev-to-current");

    constructor(className) {
        this.className = className;
    }
}

class CarouselElement {
    constructor(element) {
        this.element = element;
        this.state = CarouselElementState.HIDDEN;
        this.transition = CarouselElementTransition.NONE;
    }

    setState(newState) {
        const oldState = this.state;
        if (oldState === newState) {
            return;
        }

        if (newState.className) {
            this.element.addClass(newState.className);
        }

        if (oldState.className) {
            this.element.removeClass(oldState.className);
        }

        this.state = newState;
    }

    doTransition(newTransition) {
        const oldTransition = this.transition;
        if (oldTransition === newTransition) {
            return;
        }

        if (newTransition.className) {
            this.element.addClass(newTransition.className);
        }

        if (oldTransition.className) {
            this.element.removeClass(oldTransition.className);
        }

        this.transition = newTransition;
    }
}

class Carousel {
    constructor(containerElement, options) {
        this.pauseTime = options.pauseTime || 2000;
        this.slideInterval = null;
        this.elements = [];
        this.index = null;

        containerElement.children().each((_, _element) => {
            const element = $(_element);
            const carouselElement = new CarouselElement(element);
            this.elements.push(carouselElement);
        });

        this.set(0);
    }

    set(newIndex, change=0) {
        const oldIndex = this.index;
        if (oldIndex === newIndex) {
            return;
        }

        if (newIndex < 0 || newIndex >= this.elements.length) {
            throw new Error("Index out of range");
        }

        const newElement = this.elements[newIndex];
        if (oldIndex === null) {
            newElement.setState(CarouselElementState.CURRENT);
        } else {
            const oldElement = this.elements[oldIndex];
            if (change > 0) {
                oldElement.setState(CarouselElementState.PREV);
                oldElement.doTransition(CarouselElementTransition.TRANSITION_CURRENT_TO_PREV);
                newElement.setState(CarouselElementState.CURRENT);
                newElement.doTransition(CarouselElementTransition.TRANSITION_NEXT_TO_CURRENT);
            } else if (change < 0) {
                oldElement.setState(CarouselElementState.NEXT);
                oldElement.doTransition(CarouselElementTransition.TRANSITION_CURRENT_TO_NEXT);
                newElement.setState(CarouselElementState.CURRENT);
                newElement.doTransition(CarouselElementTransition.TRANSITION_PREV_TO_CURRENT);
            }
        }

        this.index = newIndex;
    }

    play() {
        if (!this.slideInterval) {
            this.slideInterval = setInterval(() => {
                this.next();
            }, this.pauseTime);
        }
    }

    stop() {
        if (this.slideInterval) {
            clearInterval(this.slideInterval);
            this.slideInterval = null;
        }
    }

    reset() {
        if (this.slideInterval) {
            this.stop();
            this.play();
        }
    }

    prev() {
        let prevIndex = this.index - 1;
        if (prevIndex < 0) {
            prevIndex = this.elements.length - 1;
        }

        this.set(prevIndex, -1);
        this.reset();
    }

    next() {
        let nextIndex = this.index + 1;
        if (nextIndex >= this.elements.length) {
            nextIndex = 0;
        }

        this.set(nextIndex, +1);
        this.reset();
    }
}
