//
// Created by Evgeny Nuger on 16/01/18.
//

#ifndef MULTITHREAD_WORKMANAGER_H
#define MULTITHREAD_WORKMANAGER_H


namespace workManager{
  /// interface method definitions
  class manager{

  public:
    virtual ~manager()=default;

    /// Use configure() function to set up processing queue operation structure
    /// based on the expected incoming data queue
    virtual void configure() = 0;

    /// use work() to implement the processing structure that assigns processing functions dynamically to a work queue
    /// whenever the data queue is updated
    virtual void work() = 0;
    virtual void combine() = 0;

  };

}

#endif //MULTITHREAD_WORKMANAGER_H
