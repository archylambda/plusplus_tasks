#include <map>
#include <string>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи
//enum class TaskStatus {
//	NEW,          // новая
//	IN_PROGRESS,  // в разработке
//	TESTING,      // на тестировании
//	DONE          // завершена
//};
//
//// Объявляем тип-синоним для map<TaskStatus, int>,
//// позволяющего хранить количество задач каждого статуса
//using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const{
		if (tasks.count(person)){
			return tasks.at(person);
		}
		throw logic_error("person doesn't exist");
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person){
		++tasks[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count){

		TasksInfo person_t;
		try{
			person_t = GetPersonTasksInfo(person);
		}
		catch (logic_error& exc){

		}
		TasksInfo updated_tasks, untouched_tasks = person_t;
		untouched_tasks.erase(TaskStatus::DONE);
		
		int performing_tasks = GetPerformingTasks(person);
		int performed_tasks = 0;
		for (auto& item : person_t){
			for (int i = 0; i < item.second && performed_tasks < task_count 
				&& performed_tasks < performing_tasks;
				++i, ++performed_tasks){

				if (item.first != TaskStatus::DONE){
					TaskStatus new_stat = static_cast<TaskStatus>(static_cast<int>(item.first) + 1);
					++updated_tasks[new_stat];
					--untouched_tasks[item.first];
				}
				try{
					if (!untouched_tasks.at(item.first))
						untouched_tasks.erase(item.first);
				}
				catch (out_of_range& exception){

				}
			}
		}


		updateData(person, updated_tasks, untouched_tasks);

		return tie(updated_tasks, untouched_tasks);
	}

private:

	void updateData(const string& person, const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks){

		if (tasks[person].count(TaskStatus::DONE)) {
			int done_tasks = tasks[person][TaskStatus::DONE];
			tasks[person].clear();
			tasks[person][TaskStatus::DONE] = done_tasks;
		}
		else{
			tasks[person].clear();
		}

		for (const auto& item : untouched_tasks){
			if (item.first != TaskStatus::DONE){
				tasks[person][item.first] = item.second;
			}
		}
		for (const auto& item : updated_tasks){
			tasks[person][item.first] += item.second;
		}

	}

	int GetPerformingTasks(const string& person){
		return tasks[person][TaskStatus::NEW] + tasks[person][TaskStatus::IN_PROGRESS] + tasks[person][TaskStatus::TESTING];
	}

	map<string, TasksInfo> tasks;
};

//void PrintTasksInfo(TasksInfo tasks_info) {
//	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
//}
//
//string GetTaskStatus(const TaskStatus& status){
//	switch (status)
//	{
//	case TaskStatus::NEW:
//		return "NEW";
//
//	case TaskStatus::IN_PROGRESS:
//		return "IN_PROGRESS";
//	case TaskStatus::TESTING:
//		return "TESTING";
//	case TaskStatus::DONE:
//		return "DONE";
//	default:
//		break;
//	}
//}
//
//void PrintTuple(const TasksInfo& task_tuple){
//	cout << '{';
//	for (auto& item : task_tuple){
//		 cout << GetTaskStatus(item.first) << ": " << item.second ;
//		if (!(item.first == TaskStatus::DONE))
//			cout << ", ";
//	}
//	cout << '}';
//	
//}
//
//void PrintTaskTuples(const TasksInfo& upd_t, const TasksInfo& unt_t){
//	cout << '[';
//	PrintTuple(upd_t);
//	cout << ", ";
//	PrintTuple(unt_t);
//	cout << ']' << endl;
//}
//
//int main() {
//	TeamTasks tasks;
//	for (int i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Alice");
//	}
//
//	TasksInfo updated_tasks, untouched_tasks;
//
//	tie(updated_tasks, untouched_tasks) =
//		tasks.PerformPersonTasks("Ilia", 5);
//	PrintTaskTuples(updated_tasks, untouched_tasks);
//
//	tie(updated_tasks, untouched_tasks) =
//		tasks.PerformPersonTasks("Alice", 5);
//	PrintTaskTuples(updated_tasks, untouched_tasks);
//
//	tie(updated_tasks, untouched_tasks) =
//		tasks.PerformPersonTasks("Alice", 1);
//	PrintTaskTuples(updated_tasks, untouched_tasks);
//
//	for (int i = 0; i < 5; ++i) {
//		tasks.AddNewTask("Alice");
//	}
//	tie(updated_tasks, untouched_tasks) =
//		tasks.PerformPersonTasks("Alice", 2);
//	PrintTaskTuples(updated_tasks, untouched_tasks);
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
//
//	tie(updated_tasks, untouched_tasks) =
//		tasks.PerformPersonTasks("Alice", 4);
//	PrintTaskTuples(updated_tasks, untouched_tasks);;
//	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
//
//	system("pause");
//
//	return 0;
//}