#ifndef RIME_PREDICTOR_H_
#define RIME_PREDICTOR_H_

#include <rime/processor.h>

namespace rime {

class Context;
class PredictDb;

class Predictor : public Processor {
 public:
  Predictor(const Ticket& ticket,
            PredictDb* db,
            const int max_candidates,
            const int max_iteration);
  ~Predictor();

  ProcessResult ProcessKeyEvent(const KeyEvent& key_event) override;

 protected:
  void OnContextUpdate(Context* ctx);
  void OnSelect(Context* ctx);
  void Predict(Context* ctx, const string& context_query);

 private:
  enum Action { kUnspecified, kSelect, kDelete };
  Action last_action_ = kUnspecified;
  int max_iteration_;      // prediction times limit
  int max_candidates_;     // prediction candidate count limit
  int iteration_counter_;  // times has been predicted

  PredictDb* db_;
  connection select_connection_;
  connection context_update_connection_;
};

class PredictorComponent : public Predictor::Component {
 public:
  PredictorComponent();
  virtual ~PredictorComponent();

  Predictor* Create(const Ticket& ticket) override;

 protected:
  the<PredictDb> db_;
};

}  // namespace rime

#endif  // RIME_PREDICTOR_H_
