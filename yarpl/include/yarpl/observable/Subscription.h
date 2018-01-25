// Copyright 2004-present Facebook. All Rights Reserved.

#pragma once

#include <vector>
#include <folly/Synchronized.h>

namespace yarpl {
namespace observable {

class Subscription {
 public:
  virtual ~Subscription() = default;
  virtual void cancel();
  bool isCancelled() const;

  // Adds ability to tie another subscription to this instance.
  // Whenever *this subscription is cancelled then all tied subscriptions get
  // cancelled as well
  void tieSubscription(std::shared_ptr<Subscription> subscription);

 protected:
  std::atomic<bool> cancelled_{false};
  folly::Synchronized<std::vector<std::shared_ptr<Subscription>>> tiedSubscriptions_;
};

} // observable
} // yarpl
