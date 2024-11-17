
namespace{
	class App{
		void onCaseNew(){}
		void onBankInfoAddingOneCase(){}
		void onRaising(){}
		void onProving(){}	
		void onTakingMoney(){}	
	private:
		int role;//wxuser bd
	};
}

namespace raiser{
	enum class Flow{
		BusinessDeveloperRegister
		,CaseRunning
	};
	enum class Role{
		Admin,BD
	};
	enum class Action{};
	struct FlowRoleAction{
		Flow flow;
	};
	void call(Flow flow,Role role,Action act){

	}
}
