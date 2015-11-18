#ifndef FeatureGuided_H
#define FeatureGuided_H

#include <cv.h>
#include <highgui.h>
#include <memory>

#include "BasicDataType.h"
#include "kdtree.h" // to make life easier...
#include "BasicHeader.h"

class Model;
class FeatureLine;
class ScalarField;
class KDTreeWrapper;
class tele2d;
// suppose the HIST contains 8 + 1 + 2 elements
// 8 for directions, 1 for scalar and 2 for pos (x, y)
typedef             std::vector<double>    HIST;
typedef std::vector<std::vector<double> >  HISTS;

class FeatureGuided
{
public:
  FeatureGuided(std::shared_ptr<Model> source_model, std::string targetFile);
  FeatureGuided();
  virtual ~FeatureGuided();

  void initTargetImage(std::string targetFile);
  void initRegister();
  void updateSourceVectorField();
  void updateScalarField();
  void updateSourceField(int update_type = 0);
  void updateDistSField();
  std::shared_ptr<KDTreeWrapper> getSourceKDTree();

  inline std::shared_ptr<tele2d> GetTeleRegister() { return source_tele_register; };
  inline std::shared_ptr<tele2d> GetTargetTeleRegister() { return target_tele_register; };
  inline std::shared_ptr<ScalarField> getSourceScalarField() { return source_scalar_field; };
  inline std::shared_ptr<ScalarField> getTargetScalarField() { return target_scalar_field; };
  void NormalizedTargetCurves(CURVES& curves);
  void NormalizedSourceCurves(CURVES& curves);
  void NormalizedPts(double2& pt);
  void setNormalizePara();
  void OptimizeConnection();
  double MatchScoreToVectorField(std::vector<double2>& curve);
  void BuildDispMap(const cv::Mat& source, kdtree::KDTreeArray& KDTree_data);
  void BuildSourceEdgeKDTree();
  void BuildTargetEdgeKDTree();
  void BuildEdgeKDTree(CURVES& curves, std::shared_ptr<KDTreeWrapper> kdTree);
  void GetSourceNormalizePara(double2& translate, double& scale);
  void GetFittedCurves(CURVES& curves);
  void CalculateHists(
    HISTS& hists,
    CURVES& curves, double radius, tele2d* tele);
  void SearchRadius(
    std::vector<double>& hist,
    double2 center, double r, std::vector<int2>& area,
    std::vector<double2>& vector_field, int resolution);
  void FindHistMatchCrsp(CURVES &curves);
  void GetCrspPair(CURVES& curves);
  void GetUserCrspPair(CURVES& curves, float sample_density);
  void BuildClosestPtPair();
  void GetCurrentCrspList(std::vector<std::pair<int, double2> >& crsp_list);
  void setUserCrspPair(double start[2], double end[2]);

  void ExtractCurves(const cv::Mat& source, CURVES& curves);
  void ExtractSrcCurves(const cv::Mat& source, CURVES& curves);
  void SearchCurve(const cv::Mat& source,
    int cur_row, int cur_col,
    std::vector<std::vector<bool>>& visited_table,
    std::vector<double2>& curve);


public:

  // user defined feature line
  std::shared_ptr<FeatureLine> source_vector_field_lines;
  std::shared_ptr<FeatureLine> target_vector_field_lines;

  std::vector<std::pair<int, int> > src_crsp_list;
  std::vector<std::pair<int, int> > tar_crsp_list;
  std::map<STLPairii, double2> user_correct_crsp_map;

  int user_constrained_src_v; // the index of v in model
  double2 user_constrained_tar_p; // target screen position

private:
  
  friend class ProjICP;
  friend class LargeFeatureReg;
  friend class ScalarField;

  std::shared_ptr<Model> source_model;
  cv::Mat target_img;
  cv::Mat target_edge_saliency;
  std::vector<std::vector<double2>> target_edges_sp_len; // attribute storing the length to each end of this edge for each edge sample point
  std::vector<std::vector<double> > target_edges_sp_sl;

  CURVES source_curves;
  CURVES target_curves;
  double2 curve_translate;
  double curve_scale;
  float edge_threshold; // threshold for edge detection

  std::shared_ptr<KDTreeWrapper> source_KDTree;
  std::shared_ptr<KDTreeWrapper> target_KDTree;
  std::map<int, std::pair<int, int> > kdtree_id_mapper; // map from kdtree it to curves id

  std::shared_ptr<tele2d> source_tele_register;
  std::shared_ptr<tele2d> target_tele_register;

  std::shared_ptr<ScalarField> source_scalar_field;
  std::shared_ptr<ScalarField> target_scalar_field;
private:
  FeatureGuided(const FeatureGuided&);
  void operator = (const FeatureGuided&);
};

#endif