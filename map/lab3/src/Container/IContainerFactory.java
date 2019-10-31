package Container;

import Utility.SortingStrategy;

import Container.IContainer;

public interface IContainerFactory {
    IContainer createContainer(SortingStrategy sortingStrategy);
}
