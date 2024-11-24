#include <jni.h>
#include <vector>
#include <string>
#include <algorithm>
#include "sms_SortingOperations.h"

std::vector<std::string> toVector(JNIEnv* env, jobjectArray jArray) {
    std::vector<std::string> vec;
    jsize length = env->GetArrayLength(jArray);
    for (jsize i = 0; i < length; i++) {
        jstring jstr = (jstring)env->GetObjectArrayElement(jArray, i);
        const char* cstr = env->GetStringUTFChars(jstr, NULL);
        vec.push_back(std::string(cstr));
        env->ReleaseStringUTFChars(jstr, cstr);
    }
    return vec;
}

jobjectArray toJObjectArray(JNIEnv* env, std::vector<std::string>& vec) {
    jobjectArray jArray = env->NewObjectArray(vec.size(), env->FindClass("java/lang/String"), NULL);
    for (size_t i = 0; i < vec.size(); i++) {
        env->SetObjectArrayElement(jArray, i, env->NewStringUTF(vec[i].c_str()));
    }
    return jArray;
}

extern "C" JNIEXPORT jobjectArray JNICALL Java_sms_SortingOperations_sortStudents
(JNIEnv* env, jobject obj, jobjectArray students) {
    std::vector<std::string> studentVec = toVector(env, students);

    // Sorting logic: Sort by grades
    std::sort(studentVec.begin(), studentVec.end(), [](const std::string& a, const std::string& b) {
        int gradeA = std::stoi(a.substr(a.find(",") + 1));
        int gradeB = std::stoi(b.substr(b.find(",") + 1));
        return gradeA > gradeB; // Descending order
    });

    return toJObjectArray(env, studentVec);
}
